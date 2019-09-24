<template>
  <div class="card">
    <header class="card-header">
      <p class="card-header-title level">
        Device Info
        <b-button
          @click="reload"
          outlined
          type="is-primary"
          icon-right="sync-alt"
          icon-pack="fas"
          >Reload</b-button
        >
      </p>
    </header>

    <div class="card-content columns">
      <b-field grouped group-multiline>
        <div class="control" v-for="v in deviceInfoToShow" :key="v.label">
          <b-taglist attached>
            <b-tag type="is-dark" size="is-medium">{{ v.label }}</b-tag>
            <b-tag type="is-primary" outlined size="is-medium">
              {{ v.value }}
            </b-tag>
          </b-taglist>
        </div>
      </b-field>
      <b-loading
        :is-full-page="false"
        can-cancel
        :active.sync="isLoading"
      ></b-loading>
    </div>
  </div>
</template>

<script>
import { mapActions, mapState } from 'vuex';
import range from 'lodash/range';

const scrollWaits = range(0, 10).map(v => ({
  value: v * 10,
  label: v ? `${v * 10} ms` : `Stopped`,
}));

export default {
  data() {
    return {
      isLoading: !true,
      scrollWaits,
      scrollWait: 50,
    };
  },
  computed: {
    ...mapState(['deviceInfo']),
    deviceInfoToShow() {
      if (!this.deviceInfo) return [];
      return [
        {
          label: 'Battery voltage',
          format(info) {
            return `${info.batv} mV`;
          },
        },
        {
          label: 'Uptime',
          format(info) {
            return `${info.uptime} sec`;
          },
        },
        {
          label: 'IP (Host)',
          format(info) {
            return `${info.ip_h}`;
          },
        },
        {
          label: 'IP (Client)',
          format(info) {
            return `${info.ip_c}`;
          },
        },
        {
          label: 'CPU',
          format(info) {
            return `${info.cpu_f} MHz`;
          },
        },
        {
          label: 'Flash size',
          format(info) {
            return `${info.flash_rs} bytes`;
          },
        },
        {
          label: 'Chip ID',
          format(info) {
            return `${(info.chip_id || '-').toString(16)}`;
          },
        },
        {
          label: 'Free heap',
          format(info) {
            return `${info.heap_f} bytes`;
          },
        },
        {
          label: 'mDNS',
          format(info) {
            return `${info.name}.local`;
          },
        },
      ].map(v => ({ ...v, value: v.format(this.deviceInfo) }));
    },
  },
  methods: {
    ...mapActions(['fetchDeviceInfo']),
    reload() {
      console.log('reload');
      this.fetchDeviceInfo();
    },
  },
  mounted() {
    this.fetchDeviceInfo();
  },
};
</script>
